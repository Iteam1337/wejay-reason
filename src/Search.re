type state = {searchOpen: bool};

type action =
  | DisplaySearch
  | HideSearch;

let component = ReasonReact.reducerComponent("Search");

module SearchFields = [%graphql
  {|
  mutation Search($query: String!) {
    search(query: $query) {
      album {
        images {
          url
        }
        name
        uri
      }
      artists {
        name
        uri
      }
      duration
      name
      spotifyUri
    }
  }

  |}
];

module SearchFormParams = {
  type state = {query: string};
  type fields = [ | `query];

  let lens = [(`query, s => s.query, (_s, query) => {query: query})];
};

module Styles = {
  open Css;

  let search =
    style([
      backgroundColor(rgba(0, 0, 0, 0.85)),
      bottom(px(0)),
      color(hex("fff")),
      display(grid),
      gridTemplateColumns([fr(1.0), vw(60.0), fr(1.0)]),
      left(px(0)),
      position(fixed),
      right(px(0)),
      top(px(0)),
      zIndex(10),
    ]);

  let content = style([gridColumn(2, 2), marginTop(px(100))]);

  let close =
    style([
      cursor(`pointer),
      fontSize(px(24)),
      right(px(40)),
      position(absolute),
      top(px(40)),
    ]);

  let searchIcon =
    style([
      color(rgba(36, 41, 46, 0.6)),
      cursor(`pointer),
      fontSize(px(24)),
      right(px(40)),
      position(fixed),
      top(px(40)),
      zIndex(9),
    ]);
};

module SearchMutation = ReasonApollo.CreateMutation(SearchFields);
module SearchForm = ReForm.Create(SearchFormParams);

let make = _children => {
  ...component,
  initialState: () => {searchOpen: false},
  reducer: (action, _state) =>
    switch (action) {
    | DisplaySearch => ReasonReact.Update({searchOpen: true})
    | HideSearch => ReasonReact.Update({searchOpen: false})
    },
  render: ({send, state}) =>
    state.searchOpen ?
      <SearchMutation>
        ...(
             (mutation, {result}) =>
               <SearchForm
                 initialState={query: ""}
                 onSubmit=(
                   ({values}) => {
                     let searchQuery =
                       SearchFields.make(~query=values.query, ());

                     mutation(~variables=searchQuery##variables, ()) |> ignore;
                   }
                 )
                 schema=[(`query, Required)]>
                 ...(
                      ({form, handleChange, handleSubmit}) =>
                        <div className=Styles.search>
                          <div
                            className=Styles.close
                            onClick=(_evt => send(HideSearch))>
                            <i className="icon ion-md-close" />
                          </div>
                          <form
                            className=Styles.content
                            onSubmit=(
                              ReForm.Helpers.handleDomFormSubmit(handleSubmit)
                            )>
                            <SearchInput
                              onChange=(handleChange(`query))
                              value=form.values.query
                            />
                            (
                              switch (result) {
                              | Data(result) =>
                                <SearchResults
                                  close=(() => send(HideSearch))
                                  tracks=result##search
                                />
                              | _ => ReasonReact.null
                              }
                            )
                          </form>
                        </div>
                    )
               </SearchForm>
           )
      </SearchMutation> :
      <div className=Styles.searchIcon onClick=(_evt => send(DisplaySearch))>
        <i className="icon ion-md-search" />
      </div>,
};

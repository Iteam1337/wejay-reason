open Css;

let component = ReasonReact.statelessComponent("Rooms");

module Rooms = [%graphql
  {|
    query Rooms {
      rooms {
        name
        currentTrack {
          name
          artists {
            name
            uri
          }
        }
        users {
          email
        }
      }
    }
|}
];

module RoomsQuery = ReasonApollo.CreateQuery(Rooms);

let rooms =
  style([
    display(grid),
    gridTemplateColumns([fr(1.0), px(300), fr(1.0)]),
    marginTop(px(60)),
    selector("> *", [gridColumn(2, 2)]),
  ]);

let make = _children => {
  ...component,
  render: _self =>
    <RoomsQuery>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => "Loading" |> Utils.ste
             | Error(error) =>
               Js.log(error);
               "Error" |> Utils.ste;
             | Data(response) =>
               <div className=rooms>
                 (
                   response##rooms
                   |> Js.Array.map(room =>
                        <RoomListItem key=room##name room />
                      )
                   |> ReasonReact.array
                 )
                 <AddRoom />
               </div>
             }
         )
    </RoomsQuery>,
};

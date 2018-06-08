let component = ReasonReact.statelessComponent("SearchResults");

module Styles = {
  open Css;

  let searchResults =
    style([
      display(grid),
      gridTemplateColumns([fr(1.0), fr(1.0)]),
      gridColumn(2, 2),
      marginTop(px(40)),
    ]);

  let searchTrack =
    style([
      alignItems(center),
      cursor(`pointer),
      display(grid),
      gridColumnGap(px(20)),
      gridTemplateColumns([px(40), fr(1.0)]),
      opacity(0.6),
      padding(px(10)),
      transition(~duration=150, ~timingFunction=easeInOut, "opacity"),
      selector(":hover", [opacity(1.0)]),
    ]);

  let trackArtist = style([fontSize(px(12))]);

  let trackMeta = style([fontSize(px(14)), fontWeight(600)]);
};

let make = (~close, ~tracks, _children) => {
  ...component,
  render: _self =>
    <Droparea.QueueTrackMutation>
      ...(
           (mutation, _) =>
             <div className=Styles.searchResults>
               (
                 tracks
                 |> Js.Array.map(track =>
                      <div
                        className=Styles.searchTrack
                        key=track##spotifyUri
                        onClick=(
                          _evt => {
                            let newTrack =
                              Droparea.QueueTrack.makeWithVariables({
                                "input": {
                                  "userId": Utils.userId,
                                  "spotifyId": track##spotifyUri,
                                  "roomName": "iteam",
                                },
                              });

                            mutation(
                              ~variables=newTrack##variables,
                              ~refetchQueries=[|"RoomQuery"|],
                              (),
                            )
                            |> ignore;

                            close();
                          }
                        )>
                        <Cover track />
                        <div className=Styles.trackMeta>
                          <div> (track##name |> Utils.ste) </div>
                          (
                            Js.Array.mapi(
                              (artist, i) =>
                                [|
                                  <span
                                    className=Styles.trackArtist
                                    href=artist##uri
                                    key=artist##name>
                                    (artist##name |> Utils.ste)
                                  </span>,
                                  i < Js.Array.length(track##artists) - 1 ?
                                    <span
                                      key=(artist##name ++ string_of_int(i))>
                                      (", " |> Utils.ste)
                                    </span> :
                                    ReasonReact.null,
                                |]
                                |> ReasonReact.array,
                              track##artists,
                            )
                            |> ReasonReact.array
                          )
                        </div>
                      </div>
                    )
                 |> ReasonReact.array
               )
             </div>
         )
    </Droparea.QueueTrackMutation>,
};

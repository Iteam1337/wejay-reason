open Css;
open Webapi.Dom;

type state = {isDragging: bool};

type action =
  | DragEnter
  | DragLeave;

let component = ReasonReact.reducerComponent("Droparea");

module QueueTrack = [%graphql
  {|
  mutation QueueTrack($input: QueueInput!) {
    roomQueueTrack(input: $input) {
      currentTrack {
        spotifyUri
      }
    }
  }
|}
];

let fadeIn = keyframes([(0, [opacity(0.0)]), (100, [opacity(0.2)])]);

let droparea =
  style([
    animation(
      ~duration=300,
      ~iterationCount=count(1),
      ~timingFunction=easeInOut,
      fadeIn,
    ),
    backgroundColor(hex(Theme.colors.wejay)),
    borderWidth(px(0)),
    height(pct(100.0)),
    left(px(0)),
    opacity(0.2),
    position(fixed),
    unsafe("resize", "none"),
    top(px(0)),
    width(pct(100.0)),
    selector(":focus", [outlineWidth(px(0))]),
    zIndex(10),
  ]);

module QueueTrackMutation = ReasonApollo.CreateMutation(QueueTrack);

let parseSpotifyLinks = evt =>
  ReactEventRe.Mouse.nativeEvent(evt)##dataTransfer##getData("text")
  |> Js.String.replaceByRe(
       [%re "/https:\\/\\/open.spotify.com\\/track\\//ig"],
       "",
     )
  |> Js.String.splitByRe([%re "/\\n/"], _)
  |> Js.Array.reverseInPlace;

let make = (~roomName, _children) => {
  ...component,
  initialState: () => {isDragging: false},
  reducer: (action, _state) =>
    switch (action) {
    | DragEnter => ReasonReact.Update({isDragging: true})
    | DragLeave => ReasonReact.Update({isDragging: false})
    },
  didMount: self => {
    let dragEnter = _evt => self.send(DragEnter);

    Document.addEventListener("dragenter", dragEnter, document);

    self.onUnmount(() =>
      Document.removeEventListener("dragenter", dragEnter, document)
    );
  },
  render: ({state, send}) =>
    <QueueTrackMutation>
      ...(
           (mutation, _) =>
             switch (state.isDragging) {
             | false => ReasonReact.null
             | true =>
               <textarea
                 className=droparea
                 id="droparea"
                 onDragLeave=(_evt => send(DragLeave))
                 onDrop=(
                   evt => {
                     ReactEventRe.Synthetic.stopPropagation(evt);
                     ReactEventRe.Synthetic.preventDefault(evt);

                     let spotifyTracks = parseSpotifyLinks(evt);

                     let newTrack =
                       QueueTrack.makeWithVariables({
                         "input": {
                           "userId": Utils.userId,
                           "spotifyId": spotifyTracks,
                           "roomName": roomName,
                         },
                       });

                     mutation(
                       ~variables=newTrack##variables,
                       ~refetchQueries=[|"RoomQuery"|],
                       (),
                     )
                     |> ignore;

                     send(DragLeave);
                   }
                 )
               />
             }
         )
    </QueueTrackMutation>,
};

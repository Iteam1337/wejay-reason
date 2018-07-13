let component = ReasonReact.statelessComponent("Room");

module Room = [%graphql
  {|
    query RoomQuery($roomName: String!) {
      room(name: $roomName) {
        currentTrack {
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
          started
          user {
            email
          }
        }
        users {
          email
          lastPlay
        }
        queue {
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
          user {
            email
          }
        }
      }
    }
|}
];

module RoomQuery = ReasonApollo.CreateQuery(Room);

module Styles = {
  open Css;

  let room =
    style([
      display(`grid),
      gridTemplateColumns([px(50), fr(1.0)]),
      height(vh(100.0)),
    ]);

  let roomContent = style([height(vh(100.0)), overflow(`auto)]);
};

let make = (~roomName, _children) => {
  ...component,
  render: _self => {
    let roomVariables = Room.make(~roomName, ());

    <RoomQuery pollInterval=10000 variables=roomVariables##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => "Loading" |> Utils.ste
             | Error(error) => Utils.handleErrors(error)
             | Data(response) =>
               <div className=Styles.room>
                 <Menu roomName />
                 <div className=Styles.roomContent>
                   (
                     [|
                       <NowPlaying
                         key="nowPlaying"
                         track=response##room##currentTrack
                       />,
                       <Queue key="queue" queue=response##room##queue />,
                       <Droparea key="droparea" roomName />,
                     |]
                     |> ReasonReact.array
                   )
                 </div>
               </div>
             }
         )
    </RoomQuery>;
  },
};

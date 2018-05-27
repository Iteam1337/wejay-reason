let component = ReasonReact.statelessComponent("Room");

module Room = [%graphql
  {|
    query RoomQuery($roomName: String!) {
      room(name: $roomName) {
        currentTrack {
          album {
            images {
              height
              url
              width
            }
            name
          }
          artists {
            name
          }
          duration
          name
          spotifyUri
          started
          user {
            email
            id
          }
        }
        isPlaying
        name
        users {
          email
          id
          lastPlay
        }
        queue {
          album {
            images {
              height
              url
              width
            }
            name
          }
          artists {
            name
          }
          duration
          name
          spotifyUri
          started
          user {
            email
            id
          }
        }
      }
    }
|}
];

module RoomQuery = ReasonApollo.CreateQuery(Room);

let make = (~roomName, _children) => {
  ...component,
  render: _self => {
    let roomVariables = Room.make(~roomName, ());
    <RoomQuery pollInterval=10000 variables=roomVariables##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => "Loading" |> Utils.ste
             | Error(error) =>
               Js.log(error);
               "Error" |> Utils.ste;
             | Data(response) =>
               [|
                 <NowPlaying
                   key="nowPlaying"
                   track=response##room##currentTrack
                 />,
                 <Queue key="queue" queue=response##room##queue />,
                 <Droparea key="droparea" />,
               |]
               |> ReasonReact.array
             }
         )
    </RoomQuery>;
  },
};

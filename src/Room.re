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
                 <Search key="search" />,
                 <Queue key="queue" queue=response##room##queue />,
                 <Droparea key="droparea" />,
               |]
               |> ReasonReact.array
             }
         )
    </RoomQuery>;
  },
};

let component = ReasonReact.statelessComponent("Room");

module Room = [%graphql
  {|
    query RoomQuery {
      room(name: "iteam") {
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

let make = _children => {
  ...component,
  render: _self =>
    <RoomQuery>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => "No Data" |> Utils.ste
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
    </RoomQuery>,
};

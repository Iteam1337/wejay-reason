let component = ReasonReact.statelessComponent("Rooms");

module Rooms = [%graphql
  {|
    query rooms {
      rooms {
        name
        currentTrack {
          name
          artists {
            name
          }
        }
        users {
          email
        }
      }
    }
|}
];

module JoinRoom = [%graphql
  {|
    mutation joinRoom($input: JoinRoomInput!) {
      joinRoom(input: $input) {
        name
      }
    }
|}
];

module JoinRoomMutation = ReasonApollo.CreateMutation(JoinRoom);
module RoomsQuery = ReasonApollo.CreateQuery(Rooms);

let make = _children => {
  ...component,
  render: _self =>
    <RoomsQuery>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => "No Data" |> Utils.ste
             | Loading => "Loading" |> Utils.ste
             | Error(error) =>
               Js.log(error);
               "Error" |> Utils.ste;
             | Data(response) =>
               <JoinRoomMutation>
                 ...(
                      (mutation, _) => {
                        let roomList =
                          Js.Array.map(
                            room =>
                              <div
                                key=room##name
                                onClick=(
                                  _evt => {
                                    let newUser =
                                      JoinRoom.makeWithVariables({
                                        "input": {
                                          "email": Utils.userEmail,
                                          "roomName": room##name,
                                        },
                                      });

                                    mutation(
                                      ~variables=newUser##variables,
                                      ~refetchQueries=[||],
                                      (),
                                    )
                                    |> {
                                      ReasonReact.Router.push(
                                        "/room/" ++ room##name,
                                      );
                                      ignore;
                                    };
                                  }
                                )>
                                (room##name |> Utils.ste)
                              </div>,
                            response##rooms,
                          )
                          |> ReasonReact.array;

                        <div> roomList </div>;
                      }
                    )
               </JoinRoomMutation>
             }
         )
    </RoomsQuery>,
};

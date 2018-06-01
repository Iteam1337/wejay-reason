open Css;

let component = ReasonReact.statelessComponent("RoomListItem");

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

let roomListItem =
  style([
    border(px(1), solid, hex("efefef")),
    borderRadius(px(4)),
    color(hex("333")),
    cursor(`pointer),
    padding(px(20)),
    transition(~duration=150, ~timingFunction=easeInOut, "background-color"),
    selector(":hover", [backgroundColor(rgba(54, 116, 152, 0.15))]),
  ]);

let roomInfo =
  style([
    color(hex("999")),
    display(`flex),
    flexDirection(column),
    fontSize(px(12)),
  ]);

let make = (~room, _children) => {
  ...component,
  render: _self =>
    <JoinRoomMutation>
      ...(
           (mutation, _) => {
             let users = room##users |> Js.Array.length;

             <div
               className=roomListItem
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
                     ReasonReact.Router.push("/room/" ++ room##name);
                     ignore;
                   };
                 }
               )>
               (room##name |> Utils.ste)
               <div>
                 <div className=roomInfo>
                   (
                     switch (room##currentTrack) {
                     | None => "Nothing playing" |> Utils.ste
                     | Some(track) =>
                       <div>
                         <Artists track />
                         (" - " ++ track##name |> Utils.ste)
                       </div>
                     }
                   )
                   <div>
                     (users |> string_of_int |> Utils.ste)
                     ((users == 1 ? " wejay" : " wejay") |> Utils.ste)
                   </div>
                 </div>
               </div>
             </div>;
           }
         )
    </JoinRoomMutation>,
};

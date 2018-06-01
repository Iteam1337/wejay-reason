open Css;

let component = ReasonReact.statelessComponent("AddRoom");

module AddRoom = [%graphql
  {|
    mutation AddRoom($roomName: String!) {
      addRoom(roomName: $roomName) {
        name
      }
    }
|}
];

module AddRoomMutation = ReasonApollo.CreateMutation(AddRoom);

module AddRoomParams = {
  type state = {roomName: string};
  type fields = [ | `roomName];
  /* (fieldName, getter, setter) */
  let lens = [
    (`roomName, s => s.roomName, (_s, roomName) => {roomName: roomName}),
  ];
};

let addRoom = style([]);

let addRoomForm = style([gridColumn(2, 2), marginTop(px(50))]);

module AddRoomForm = ReForm.Create(AddRoomParams);

let make = _children => {
  ...component,
  render: _self =>
    <AddRoomMutation>
      ...(
           (mutation, _) =>
             <AddRoomForm
               onSubmit=(
                 ({values}) => {
                   let newRoom = AddRoom.make(~roomName=values.roomName, ());

                   mutation(
                     ~variables=newRoom##variables,
                     ~refetchQueries=[|"Rooms"|],
                     (),
                   )
                   |> ignore;
                 }
               )
               initialState={roomName: ""}
               schema=[(`roomName, Required)]>
               ...(
                    ({form, handleChange, handleSubmit, getErrorForField}) =>
                      <div className=addRoom>
                        <form
                          className=addRoomForm
                          onSubmit=(
                            ReForm.Helpers.handleDomFormSubmit(handleSubmit)
                          )>
                          <Input
                            _type="text"
                            label="Room name"
                            onChange=(handleChange(`roomName))
                            value=form.values.roomName
                          />
                          <p>
                            (
                              getErrorForField(`roomName)
                              |> Belt.Option.getWithDefault(_, "")
                              |> ReasonReact.string
                            )
                          </p>
                          <button _type="submit" className="button">
                            ("Add room" |> Utils.ste)
                          </button>
                        </form>
                      </div>
                  )
             </AddRoomForm>
         )
    </AddRoomMutation>,
};

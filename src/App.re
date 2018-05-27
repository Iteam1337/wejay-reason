open Dom.Storage;

type action =
  | Login
  | Room(string)
  | Rooms
  | Unknown;

type state = {currentPage: action};

let component = ReasonReact.reducerComponent("App");

let initialPage = () =>
  switch (ReasonReact.Router.dangerouslyGetInitialUrl().path) {
  | ["login"] => Login
  | ["room", roomName] => Room(roomName)
  | ["rooms"] => Rooms
  | _ =>
    switch (localStorage |> getItem("email")) {
    | None => Login
    | Some(_email) => Rooms
    }
  };

let make = _children => {
  ...component,
  initialState: () => {currentPage: initialPage()},
  reducer: (action, _state) =>
    switch (action) {
    | Login => ReasonReact.Update({currentPage: Login})
    | Room(roomName) => ReasonReact.Update({currentPage: Room(roomName)})
    | Rooms => ReasonReact.Update({currentPage: Rooms})
    | Unknown => ReasonReact.Update({currentPage: Unknown})
    },
  didMount: self =>
    ReasonReact.Router.push(
      switch (self.state.currentPage) {
      | Login => "/login"
      | Room(roomName) => "/room/" ++ roomName
      | Rooms => "/rooms"
      | Unknown => "/"
      },
    ),
  render: ({state}) =>
    switch (state.currentPage) {
    | Room(_roomName) => <Room />
    | Rooms => <Rooms />
    | Login => <Login />
    | Unknown => "Unknown page" |> Utils.ste
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch (url.path) {
          | ["login"] => self.send(Login)
          | ["room", roomName] => self.send(Room(roomName))
          | ["rooms"] => self.send(Rooms)
          | _ => self.send(Unknown)
          }
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
};

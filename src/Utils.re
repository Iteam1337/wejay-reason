open Dom.Storage;

[@bs.module] external md5 : string => string = "";

let ste = ReasonReact.string;

let userId =
  switch (localStorage |> getItem("email")) {
  | None => ""
  | Some(email) => md5(email)
  };

let userEmail =
  switch (localStorage |> getItem("email")) {
  | None => ""
  | Some(email) => email
  };

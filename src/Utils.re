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

/*
   TODO: Fix gqlError when reason-apollo fixes
   the error type, should be error##message
 */
let handleErrors = error => {
  let gqlErrors = Js.Nullable.toOption(error##graphQLErrors);
  let networkError = Js.Nullable.toOption(error##networkError);

  switch (gqlErrors, networkError) {
  | (None, None) => ReasonReact.null
  | (Some(errors), _) =>
    errors
    |> Js.Array.map(error => <div key=error> (error |> ste) </div>)
    |> ReasonReact.array
  | (None, Some(errors)) => <div> (errors |> ste) </div>
  };
};

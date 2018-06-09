[@bs.module] external md5 : string => string = "";

let component = ReasonReact.statelessComponent("Login");

module LoginParams = {
  type state = {email: string};
  type fields = [ | `email];
  /* (fieldName, getter, setter) */
  let lens = [(`email, s => s.email, (_s, email) => {email: email})];
};

module LoginForm = ReForm.Create(LoginParams);

module Styles = {
  open Css;

  let form = style([
    marginLeft(`auto),
    marginRight(`auto),
    marginTop(px(60)),
    width(px(400))
  ]);

  let avatar = style([marginTop(px(-70)), paddingBottom(px(20))]);

  let avatarImage =
    style([
      background(hex("fff")),
      borderRadius(pct(50.0)),
      boxShadow(~y=px(2), ~blur=px(5), rgba(10, 10, 10, 0.1)),
      padding(px(5)),
    ]);
};

let make = _children => {
  ...component,
  render: _self =>
    <LoginForm
      onSubmit=(
        ({values}) => {
          Dom.Storage.(localStorage |> setItem("email", values.email));
          ReasonReact.Router.push("/rooms");
        }
      )
      initialState={email: ""}
      schema=[(`email, Email)]>
      ...(
           ({form, getErrorForField, handleChange, handleSubmit}) =>
             <form
               className=Styles.form
               onSubmit=(ReForm.Helpers.handleDomFormSubmit(handleSubmit))>
               <Input
                 id="email"
                 type_="email"
                 helpText="E-mail address is used to fetch Gravatar"
                 label="E-mail address"
                 onChange=(handleChange(`email))
                 value=form.values.email
               />
               <p>
               (
                 getErrorForField(`email)
                 |> Belt.Option.getWithDefault(_, "")
                 |> ReasonReact.string
               )
             </p>
               <Button type_="submit">
                 ...("Save e-mail" |> Utils.ste)
               </Button>
             </form>
         )
    </LoginForm>,
};

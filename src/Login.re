open Css;

[@bs.module] external md5 : string => string = "";

let component = ReasonReact.statelessComponent("Login");

module LoginParams = {
  type state = {email: string};
  type fields = [ | `email];
  /* (fieldName, getter, setter) */
  let lens = [(`email, s => s.email, (_s, email) => {email: email})];
};

module LoginForm = ReForm.Create(LoginParams);

let avatar = style([marginTop(px(-70)), paddingBottom(px(20))]);

let avatarImage =
  style([
    background(hex("fff")),
    borderRadius(pct(50.0)),
    boxShadow(~y=px(2), ~blur=px(5), rgba(10, 10, 10, 0.1)),
    padding(px(5)),
  ]);

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
           ({form, handleChange, handleSubmit}) =>
             <section className="hero has-background-light is-fullheight">
               <div className="hero-body">
                 <div className="container has-text-centered">
                   <div className="column is-4 is-offset-4">
                     <div className="box">
                       <figure className=avatar>
                         <img
                           className=avatarImage
                           src=(
                             "https://www.gravatar.com/avatar/"
                             ++ md5(form.values.email)
                             ++ "?size=128"
                           )
                         />
                       </figure>
                       <form
                         onSubmit=(
                           ReForm.Helpers.handleDomFormSubmit(handleSubmit)
                         )>
                         <Input
                           helpText="E-mail address is used to fetch Gravatar"
                           label="E-mail address"
                           onChange=(handleChange(`email))
                           value=form.values.email
                         />
                         <button _type="submit" className="button is-primary">
                           ("Save e-mail" |> Utils.ste)
                         </button>
                       </form>
                     </div>
                   </div>
                 </div>
               </div>
             </section>
         )
    </LoginForm>,
};
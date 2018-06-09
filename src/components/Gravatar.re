open Css;

[@bs.module] external md5 : string => string = "";

let component = ReasonReact.statelessComponent("Artists");

let gravatar = style([borderRadius(pct(100.0)), verticalAlign(`top)]);

let make = (~size="30px", ~track, _children) => {
  ...component,
  render: _self =>
    switch (track##user) {
    | Some(user) =>
      <img
        className=gravatar
        src=("https://www.gravatar.com/avatar/" ++ md5(user##email))
        style=(ReactDOMRe.Style.make(~height=size, ~width=size, ()))
      />
    | None => ReasonReact.null
    },
};

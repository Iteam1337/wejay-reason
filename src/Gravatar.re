open Css;

[@bs.module] external md5 : string => string = "";

let component = ReasonReact.statelessComponent("Artists");

let gravatar =
  style([borderRadius(pct(100.0)), height(px(30)), width(px(30))]);

let make = (~track, _children) => {
  ...component,
  render: _self =>
    switch (track##user) {
    | Some(user) =>
      <img
        className=gravatar
        src=("https://www.gravatar.com/avatar/" ++ md5(user##email))
      />
    | None => ReasonReact.null
    },
};

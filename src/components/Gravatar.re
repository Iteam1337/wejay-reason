open Css;

[@bs.module] external md5 : string => string = "";

let component = ReasonReact.statelessComponent("Artists");

let gravatar = style([borderRadius(pct(100.0)), verticalAlign(`top)]);

let make = (~size="30px", ~track, _children) => {
  ...component,
  render: _self =>
    <img
      className=gravatar
      src=("https://www.gravatar.com/avatar/" ++ md5(track##user##email))
      style=(ReactDOMRe.Style.make(~height=size, ~width=size, ()))
    />,
};

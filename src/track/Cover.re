open Css;

let component = ReasonReact.statelessComponent("Cover");

let coverImage =
  style([borderRadius(px(2)), height(px(40)), width(px(40))]);

let make = (~track, _children) => {
  ...component,
  render: _self => {
    let firstCover = track##album##images |> Array.to_list |> List.nth(_, 0);
    <img className=coverImage key=firstCover##url src=firstCover##url />;
  },
};

open Css;

let component = ReasonReact.statelessComponent("Cover");

let cover = style([position(relative)]);

let coverImage =
  style([
    borderRadius(px(3)),
    position(relative),
    verticalAlign(`top),
    zIndex(2),
  ]);

let coverShadow =
  style([
    bottom(px(-25)),
    left(px(0)),
    position(absolute),
    transform(scale(0.9, 0.9)),
    zIndex(1),
    unsafe("filter", "blur(15px)"),
  ]);

let make = (~size="40px", ~track, _children) => {
  ...component,
  render: _self => {
    let firstCover = track##album##images |> Array.to_list |> List.nth(_, 0);
    let isSmall = size == "40px";

    <div className=cover>
      <img
        className=coverImage
        src=firstCover##url
        style=(ReactDOMRe.Style.make(~height=size, ~width=size, ()))
      />
      (
        isSmall ?
          ReasonReact.null :
          <img
            className=coverShadow
            src=firstCover##url
            style=(ReactDOMRe.Style.make(~height=size, ~width=size, ()))
          />
      )
    </div>;
  },
};

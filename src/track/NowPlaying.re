open Css;

let component = ReasonReact.statelessComponent("NowPlaying");

let nowPlaying =
  style([
    backgroundColor(hex("fff")),
    display(grid),
    height(px(300)),
    padding(px(20)),
    position(sticky),
    overflow(hidden),
    top(px(0)),
    unsafe("gridTemplateColumns", "1fr 1140px 1fr"),
    zIndex(2),
  ]);

let background =
  style([
    backgroundPosition(pct(50.0), pct(50.0)),
    backgroundSize(`cover),
    bottom(px(0)),
    left(px(0)),
    transform(scale(1.5, 1.5)),
    opacity(0.2),
    position(absolute),
    right(px(0)),
    top(px(0)),
    unsafe("filter", "blur(10px)"),
  ]);

let nowPlayingContent =
  style([
    alignItems(center),
    display(grid),
    gridColumnGap(px(20)),
    gridColumn(2, 2),
    unsafe("gridTemplateColumns", "auto 1fr auto auto"),
  ]);

let make = (~track, _children) => {
  ...component,
  render: _self =>
    switch (track) {
    | None => ReasonReact.null
    | Some(track) =>
      let firstCover =
        track##album##images |> Array.to_list |> List.nth(_, 0);
      <div className=nowPlaying>
        <div
          className=background
          style=(
            ReactDOMRe.Style.make(
              ~backgroundImage="url(" ++ firstCover##url ++ ")",
              (),
            )
          )
        />
        <div className=nowPlayingContent>
          <Cover track />
          <TrackMeta track />
          <TrackDuration track />
          <Gravatar track />
        </div>
      </div>;
    },
};

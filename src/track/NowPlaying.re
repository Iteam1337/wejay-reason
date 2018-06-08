open Css;

type state = {barPosition: float};

type action =
  | UpdateBar;

let component = ReasonReact.reducerComponent("NowPlaying");

let nowPlaying =
  style([
    display(grid),
    height(px(300)),
    position(relative),
    overflow(hidden),
    gridTemplateColumns([fr(1.0), vw(80.0), fr(1.0)]),
  ]);

let background =
  style([
    backgroundPosition(pct(50.0), pct(50.0)),
    backgroundSize(`cover),
    bottom(px(0)),
    left(px(0)),
    transform(scale(1.5, 1.5)),
    position(absolute),
    right(px(0)),
    top(px(0)),
    unsafe("filter", "blur(20px)"),
    zIndex(1),
  ]);

let backgroundOverlay =
  style([
    backgroundColor(rgba(255, 255, 255, 0.75)),
    bottom(px(0)),
    left(px(0)),
    position(absolute),
    right(px(0)),
    top(px(0)),
    zIndex(2),
  ]);

let nowPlayingContent =
  style([
    alignItems(flexEnd),
    bottom(px(0)),
    display(grid),
    gridColumn(2, 2),
    gridColumnGap(px(20)),
    gridTemplateColumns([auto, fr(1.0)]),
    left(px(0)),
    paddingBottom(px(40)),
    position(absolute),
    right(px(0)),
    zIndex(4),
  ]);

let overlay =
  style([
    backgroundColor(rgba(54, 116, 152, 0.2)),
    bottom(px(0)),
    left(px(0)),
    position(absolute),
    top(px(0)),
    zIndex(3),
  ]);

let trackMeta = style([lineHeight(1.4)]);

let nowPlayingArtist =
  style([
    color(hex(Theme.colors.foreground)),
    fontSize(px(21)),
    fontWeight(300),
    textDecoration(none),
    selector(":hover", [textDecoration(underline)]),
  ]);

let nowPlayingMeta =
  style([color(hex(Theme.colors.foreground)), fontSize(px(28))]);

let nowPlayingAlbum =
  style([color(hex(Theme.colors.foreground)), fontSize(px(16))]);

let make = (~track, _children) => {
  ...component,
  initialState: () => {barPosition: 0.0},
  reducer: (action, _state) =>
    switch (action) {
    | UpdateBar =>
      let barPosition =
        switch (track) {
        | None => 0.0
        | Some(track) =>
          switch (track##started) {
          | None => 0.0
          | Some(started) =>
            (Js.Date.now() -. started) /. track##duration *. float_of_int(100)
          }
        };

      ReasonReact.Update({barPosition: barPosition});
    },
  didMount: self => {
    self.send(UpdateBar);
    let intervalId = Js.Global.setInterval(() => self.send(UpdateBar), 1000);
    self.onUnmount(() => Js.Global.clearInterval(intervalId));
  },
  render: ({state}) =>
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
        <div className=backgroundOverlay />
        <div
          className=overlay
          style=(
            ReactDOMRe.Style.make(
              ~width=string_of_float(state.barPosition) ++ "%",
              (),
            )
          )
        />
        <div className=nowPlayingContent>
          <Cover size="200px" track />
          <div>
            <Gravatar track />
            <div className=trackMeta>
              <div className=nowPlayingMeta> (track##name |> Utils.ste) </div>
              <Artists className=nowPlayingArtist track />
              <div className=nowPlayingAlbum>
                (track##album##name |> Utils.ste)
              </div>
            </div>
          </div>
        </div>
      </div>;
    },
};

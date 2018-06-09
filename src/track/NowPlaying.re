[@bs.val] [@bs.module "track-duration"] external parse : int => string = "";

type state = {
  barPosition: float,
  songPosition: float,
};

type action =
  | UpdateBar;

let component = ReasonReact.reducerComponent("NowPlaying");

module Styles = {
  open Css;

  let nowPlaying =
    style([
      display(`grid),
      height(px(300)),
      position(`relative),
      overflow(`hidden),
      gridTemplateColumns([fr(1.0), vw(80.0), fr(1.0)]),
    ]);

  let background =
    style([
      backgroundPosition(pct(50.0), pct(50.0)),
      backgroundSize(`cover),
      bottom(px(0)),
      left(px(0)),
      opacity(0.5),
      position(`absolute),
      transform(scale(1.5, 1.5)),
      unsafe("filter", "blur(10px)"),
      right(px(0)),
      top(px(0)),
      zIndex(1),
    ]);

  let backgroundOverlay =
    style([
      backgroundColor(rgba(255, 255, 255, 0.6)),
      bottom(px(0)),
      left(px(0)),
      position(`absolute),
      right(px(0)),
      top(px(0)),
      zIndex(2),
    ]);

  let nowPlayingContent =
    style([
      alignItems(`center),
      bottom(px(0)),
      display(`grid),
      gridColumn(2, 2),
      gridColumnGap(px(40)),
      gridTemplateColumns([auto, fr(1.0)]),
      left(px(0)),
      paddingBottom(px(40)),
      position(`absolute),
      right(px(0)),
      zIndex(4),
    ]);

  let overlay =
    style([
      backgroundColor(rgba(54, 116, 152, 0.2)),
      bottom(px(0)),
      left(px(0)),
      position(`absolute),
      top(px(0)),
      zIndex(3),
    ]);

  let trackMeta = style([lineHeight(1.4)]);

  let nowPlayingMeta =
    style([
      color(hex(Theme.colors.foreground)),
      fontSize(em(2.0)),
      fontWeight(400),
      lineHeight(1.1),
    ]);

  let nowPlayingArtist =
    style([
      color(hex(Theme.colors.foreground)),
      fontSize(em(1.7411)),
      fontWeight(300),
      lineHeight(1.75),
      textDecoration(`none),
      selector(":hover", [textDecoration(`underline)]),
    ]);

  let nowPlayingAlbum =
    style([
      alignItems(`center),
      color(hex(Theme.colors.foreground)),
      display(`flex),
      fontSize(em(0.8706)),
    ]);

  let gravatarWrap = style([marginLeft(px(5))]);
};

let make = (~track, _children) => {
  ...component,
  initialState: () => {barPosition: 0.0, songPosition: 0.0},
  reducer: (action, _state) =>
    switch (action) {
    | UpdateBar =>
      let (barPosition, songPosition) =
        switch (track) {
        | None => (0.0, 0.0)
        | Some(track) =>
          switch (track##started) {
          | None => (0.0, 0.0)
          | Some(started) =>
            let currentTime = Js.Date.now() -. started;

            (
              currentTime /. track##duration *. float_of_int(100),
              currentTime > track##duration ? track##duration : currentTime,
            );
          }
        };

      ReasonReact.Update({barPosition, songPosition});
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
      <div className=Styles.nowPlaying>
        <div
          className=Styles.background
          style=(
            ReactDOMRe.Style.make(
              ~backgroundImage="url(" ++ firstCover##url ++ ")",
              (),
            )
          )
        />
        <div className=Styles.backgroundOverlay />
        <div
          className=Styles.overlay
          style=(
            ReactDOMRe.Style.make(
              ~width=string_of_float(state.barPosition) ++ "%",
              (),
            )
          )
        />
        <div className=Styles.nowPlayingContent>
          <Cover size="200px" track />
          <div>
            <div className=Styles.trackMeta>
              <div className=Styles.nowPlayingMeta>
                (track##name |> Utils.ste)
              </div>
              <Artists className=Styles.nowPlayingArtist track />
              <div className=Styles.nowPlayingAlbum>
                (
                  track##album##name
                  ++ {js| • |js}
                  ++ parse(int_of_float(state.songPosition))
                  ++ " / "
                  ++ parse(int_of_float(track##duration))
                  ++ {js| • |js}
                  |> Utils.ste
                )
                <span className=Styles.gravatarWrap>
                  <Gravatar size="20px" track />
                </span>
              </div>
            </div>
          </div>
        </div>
      </div>;
    },
};

let component = ReasonReact.statelessComponent("Queue");

module Styles = {
  open Css;
  let gridRow =
    style([
      display(grid),
      gridTemplateColumns([fr(1.0), vw(80.0), fr(1.0)]),
      paddingBottom(px(40)),
      paddingTop(px(40)),
      position(relative),
      zIndex(1),
    ]);

  let gridHead =
    style([
      alignItems(center),
      borderBottom(px(1), solid, hex("eaecef")),
      color(rgba(36, 41, 46, 0.6)),
      display(none),
      gridColumn(2, 2),
      gridColumnGap(px(20)),
      fontSize(px(12)),
      paddingBottom(px(15)),
      paddingTop(px(15)),
      media(
        "(min-width: 768px)",
        [
          display(grid),
          gridTemplateColumns([
            px(20),
            px(40),
            fr(1.0),
            fr(1.0),
            fr(1.0),
            px(50),
            px(30),
          ]),
        ],
      ),
    ]);

  let trackRow =
    style([
      alignItems(center),
      borderBottom(px(1), solid, hex("eaecef")),
      color(hex(Theme.colors.foreground)),
      display(`grid),
      gridColumn(2, 2),
      gridColumnGap(px(20)),
      fontSize(px(12)),
      paddingBottom(px(15)),
      paddingTop(px(15)),
      gridTemplateColumns([
        px(20),
        auto,
        fr(1.0),
        fr(1.0),
        fr(1.0),
        px(50),
        px(30),
      ]),
      media("(max-width: 768px)", [gridTemplateColumns([fr(1.0)])]),
    ]);

  let trackNumberClass =
    style([media("(max-width: 768px)", [display(none)])]);

  let durationColumn =
    style([
      textAlign(`left),
      media("(min-width: 1025px)", [textAlign(`right)]),
    ]);

  let trackName =
    style([
      color(hex("363d43")),
      textDecoration(none),
      selector(":hover", [textDecoration(underline)]),
    ]);

  let emptyList =
    style([
      alignItems(center),
      border(px(1), solid, hex("eaecef")),
      borderRadius(px(3)),
      display(`flex),
      gridColumn(2, 2),
      justifyContent(center),
      marginTop(px(20)),
      padding(px(40)),
    ]);

  let queueDuration = style([textAlign(`right)]);
};

let trackNumber = number =>
  if (number < 10) {
    "0" ++ string_of_int(number);
  } else {
    string_of_int(number);
  };

let make = (~queue, _children) => {
  ...component,
  render: _self =>
    <section className=Styles.gridRow>
      <div className=Styles.gridHead>
        <div> ("#" |> Utils.ste) </div>
        <div />
        <div> ("Title" |> Utils.ste) </div>
        <div> ("Artist" |> Utils.ste) </div>
        <div> ("Album" |> Utils.ste) </div>
        <div className=Styles.durationColumn> ("Duration" |> Utils.ste) </div>
        <div> ("Player" |> Utils.ste) </div>
      </div>
      (
        switch (Js.Array.length(queue) > 0) {
        | false =>
          <div className=Styles.emptyList>
            ("Queue is empty" |> Utils.ste)
          </div>
        | true =>
          queue
          |> Js.Array.mapi((track, i) =>
               <div className=Styles.trackRow key=track##spotifyUri>
                 <div className=Styles.trackNumberClass>
                   (trackNumber(i + 1) |> Utils.ste)
                 </div>
                 <Cover track />
                 <a className=Styles.trackName href=track##spotifyUri>
                   (track##name |> Utils.ste)
                 </a>
                 <Artists track />
                 <a className=Styles.trackName href=track##album##uri>
                   (track##album##name |> Utils.ste)
                 </a>
                 <div className=Styles.queueDuration>
                   <TrackDuration track />
                 </div>
                 <Gravatar track />
               </div>
             )
          |> ReasonReact.array
        }
      )
    </section>,
};

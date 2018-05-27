open Css;

let component = ReasonReact.statelessComponent("Queue");

let gridRow =
  style([
    display(grid),
    /* Replace when this gets pushed to a new version https://github.com/SentiaAnalytics/bs-css/commit/2be0bfdaec448c7ce17a564cd5f7c4d269acf2c8 */
    paddingBottom(px(40)),
    paddingTop(px(40)),
    position(relative),
    unsafe("gridTemplateColumns", "1fr 1140px 1fr"),
    zIndex(1),
  ]);

let gridHead =
  style([
    alignItems(center),
    borderBottom(px(1), solid, hex("eaecef")),
    color(rgba(54, 61, 67, 0.6)),
    display(grid),
    gridColumn(2, 2),
    gridColumnGap(px(20)),
    fontSize(px(12)),
    paddingBottom(px(15)),
    paddingTop(px(15)),
    unsafe("gridTemplateColumns", "20px 40px 1fr 1fr 1fr 50px 30px"),
  ]);

let trackRow =
  style([
    alignItems(center),
    borderBottom(px(1), solid, hex("eaecef")),
    color(hex("363d43")),
    display(grid),
    gridColumn(2, 2),
    gridColumnGap(px(20)),
    fontSize(px(12)),
    paddingBottom(px(15)),
    paddingTop(px(15)),
    /* Replace when this gets pushed to a new version https://github.com/SentiaAnalytics/bs-css/commit/2be0bfdaec448c7ce17a564cd5f7c4d269acf2c8 */
    unsafe("gridTemplateColumns", "20px auto 1fr 1fr 1fr 50px 30px"),
  ]);

let durationColumn = style([textAlign(`right)]);

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

let trackNumber = number =>
  if (number < 10) {
    "0" ++ string_of_int(number);
  } else {
    string_of_int(number);
  };

let make = (~queue, _children) => {
  ...component,
  render: _self =>
    <section className=gridRow>
      <div className=gridHead>
        <div> ("#" |> Utils.ste) </div>
        <div />
        <div> ("Title" |> Utils.ste) </div>
        <div> ("Artist" |> Utils.ste) </div>
        <div> ("Album" |> Utils.ste) </div>
        <div className=durationColumn> ("Duration" |> Utils.ste) </div>
        <div> ("Player" |> Utils.ste) </div>
      </div>
      (
        switch (Js.Array.length(queue) > 0) {
        | false =>
          <div className=emptyList> ("Queue is empty" |> Utils.ste) </div>
        | true =>
          Js.Array.mapi(
            (track, i) =>
              <div className=trackRow key=track##spotifyUri>
                <div> (trackNumber(i + 1) |> Utils.ste) </div>
                <Cover track />
                <a className=trackName href=track##spotifyUri>
                  (track##name |> Utils.ste)
                </a>
                <Artists track />
                <a className=trackName href=track##album##uri>
                  (track##album##name |> Utils.ste)
                </a>
                <TrackDuration track />
                <Gravatar track />
              </div>,
            queue,
          )
          |> ReasonReact.array
        }
      )
    </section>,
};

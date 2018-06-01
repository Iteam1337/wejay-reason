open Css;

let component = ReasonReact.statelessComponent("Artists");

let artistItem =
  style([
    color(hex(Theme.colors.foreground)),
    textDecoration(none),
    selector(":hover", [textDecoration(underline)]),
  ]);

let make = (~className=artistItem, ~track, _children) => {
  ...component,
  render: _self =>
    <span>
      (
        Js.Array.mapi(
          (artist, i) =>
            [|
              <a className href=artist##uri key=artist##name>
                (artist##name |> Utils.ste)
              </a>,
              i < Js.Array.length(track##artists) - 1 ?
                <span key=(artist##name ++ string_of_int(i))>
                  (", " |> Utils.ste)
                </span> :
                ReasonReact.null,
            |]
            |> ReasonReact.array,
          track##artists,
        )
        |> ReasonReact.array
      )
    </span>,
};

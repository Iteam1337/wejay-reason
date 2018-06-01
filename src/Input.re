let component = ReasonReact.statelessComponent("Input");

let make = (~_type, ~helpText=?, ~label, ~onChange, ~value, _children) => {
  ...component,
  render: _self =>
    <div className="field">
      <div className="control">
        <label className="label" htmlFor="email"> (label |> Utils.ste) </label>
        <input
          _type
          className="input is-medium"
          id="email"
          onChange=(ReForm.Helpers.handleDomFormChange(onChange))
          value
        />
      </div>
      (
        switch (helpText) {
        | Some(text) =>
          <p className="help has-text-left"> (text |> Utils.ste) </p>
        | None => ReasonReact.null
        }
      )
    </div>,
};

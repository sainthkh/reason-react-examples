
let boardValueToString = squareValue =>
    switch(squareValue) {
    | `O => "O"
    | `X => "X"
    | `Empty => ""
    }

let component = ReasonReact.statelessComponent("Square");

let make = (~value, ~onClick, _children) => {
    ...component,
    render: _self => {
        <div className="square" onClick>
            {ReasonReact.string(boardValueToString(value))}
        </div>
    }
}
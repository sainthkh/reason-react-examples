let component = ReasonReact.statelessComponent("Hello");

let make = (_children) => {
    ...component,
    render: _self => 
        <h1>{ReasonReact.string("Hello, World!")}</h1>
}
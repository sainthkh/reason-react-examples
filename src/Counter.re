type state = {
  count: int,
};

type action = 
  | Count 
  | Reset;

let component = ReasonReact.reducerComponent("Counter");

let make = (~initialNumber: int, _children) => {
    ...component,

    initialState: () => { count: initialNumber },

    reducer: (action, state) => 
        switch(action) {
        | Count => ReasonReact.Update({ count: state.count + 1 })
        | Reset => ReasonReact.Update({ count: initialNumber })
        },

    render: (self) => {
        <div>
            <h1>{ReasonReact.string("Counter")}</h1>
            <div>{ReasonReact.string(string_of_int(self.state.count))}</div>
            <div><button onClick={_event => self.send(Count)}>{ReasonReact.string("Count")}</button></div>
            <div><button onClick={_event => self.send(Reset)}>{ReasonReact.string("Reset")}</button></div>
        </div>
    }
}

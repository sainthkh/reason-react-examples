type state = {
    isOn: bool,
}

type action = Click;

let component = ReasonReact.reducerComponent("OnOff");

let make = (~default: bool, _children) => {
    ...component,
    initialState: () => {
        isOn: default,
    },

    reducer: (action, state) => {
        switch(action) {
        | Click => ReasonReact.Update({...state, isOn: !state.isOn})
        }
    },

    render: self => {
        <div>
            <h1>{ReasonReact.string("On/Off")}</h1>
            <p>{ReasonReact.string(self.state.isOn? "On": "Off")}</p>
            <button onClick={_event => self.send(Click)}>{ReasonReact.string("Click Here!")}</button>
        </div>
    }
}
[@bs.new] external createDate : unit => Js.Date.t = "Date";

type state = {
    time : string,
    timerId: ref(option(Js.Global.intervalId)),
}

type action = Update;

let component = ReasonReact.reducerComponent("Clock");

let make = (_children) => {
    ...component,

    initialState: () => {
        time: "",
        timerId: ref(None),
    },

    reducer: (action, state) => 
        switch(action) {
        | Update => ReasonReact.Update({...state, time: Js.Date.toLocaleTimeString(createDate())})
        },

    didMount: (self) => {
        self.state.timerId := Some(Js.Global.setInterval(() => {
            self.send(Update);
        }, 1000));
    },

    willUnmount: (self) => 
        switch(self.state.timerId^) {
        | Some(id) => Js.Global.clearInterval(id);
        | None => Js.log("Error clearing interval");
        },

    render: self => 
        <div>
            <h1>{ReasonReact.string("Timer")}</h1>
            <div>{ReasonReact.string(self.state.time)}</div>
        </div>
}
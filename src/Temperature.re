type tempType = Celcius | Fahrenheit;

let tempTypeString = (tempType) => 
    switch(tempType) {
    | Celcius => "Celcius"
    | Fahrenheit => "Fahrenheit"
    }

let string_of_temperature = (temperature: option(float)) => 
    switch(temperature) {
    | None => ""
    | Some(t) when (t -. floor(t)) == 0. => string_of_int(int_of_float(t))
    | Some(t) => string_of_float(t)
    }


let component = ReasonReact.statelessComponent("Temperature");

let make = (~tempType: tempType, ~temperature: string, ~onTemperatureChange, _children) => {
    let onChange = (event, _self) => {
        let t = ReactEvent.Form.target(event)##value;
        onTemperatureChange(tempType, t)
    };

    {
        ...component,

        render: self => {
            <div>
                <p>{ReasonReact.string("Type in temperature in " ++ tempTypeString(tempType))}</p>
                <input type_="text" value=temperature onChange={ self.handle(onChange) }/>
            </div>
        }
    }
}

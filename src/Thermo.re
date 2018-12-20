type state = {
    temperature: string,
    tempType: Temperature.tempType,
}

type action = ChangeTemperature(Temperature.tempType, string);

let component = ReasonReact.reducerComponent("Thermo");

let fahrenheitToCelcius = (f) => (f -. 32.0) *. 5.0 /. 9.0;
let celciusToFahrenheit = (c) => c *. 1.8 +. 32.0;
let convertTemperature = (tempType: Temperature.tempType, value) => 
    switch(tempType) {
    | Celcius => fahrenheitToCelcius(value)
    | Fahrenheit => celciusToFahrenheit(value)
    }

let make = (_children) => {
    ...component, 
    initialState: () => {
        temperature: "",
        tempType: Celcius,
    },

    reducer: (action, _state) => 
        switch(action) {
        | ChangeTemperature(tempType, temperature) => ReasonReact.Update({ tempType, temperature })
        },

    render: ({send, state}) => {
        let onTemperatureChange = (tempType, temperature) => 
            send(ChangeTemperature(tempType, temperature));
        
        let temperatureValue = (tempType, temperature) => 
            switch(temperature) {
            | "" => ""
            | _ when state.tempType == tempType => temperature
            | _ => string_of_float(convertTemperature(tempType, float_of_string(temperature)))
            }
        
        let c = temperatureValue(Celcius, state.temperature);
        let f = temperatureValue(Fahrenheit, state.temperature);
            
        <div>
            <Temperature tempType=Celcius temperature=c onTemperatureChange />
            <Temperature tempType=Fahrenheit temperature=f onTemperatureChange />
        </div>
    }
}
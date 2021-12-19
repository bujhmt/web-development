import React from 'react';
import {InfoCard} from "./components/info-card";

function App() {

    return (
        <div className="app">
            <h1>Lab4.2</h1>
            <InfoCard name="mpstat"/>
            <InfoCard name="iostat"/>
            <InfoCard name="free"/>
        </div>
    );
}

export default App;

import React, {useEffect, useState} from 'react';
import {BASE_URI} from "../constants";

interface Params {
    name: string;
}

export function InfoCard({name}: Params) {
    const [value, setValue] = useState<string>('');
    const updateInterval = 1000;

    useEffect(() => {
        const interval = setInterval(() => {
            fetch(`${BASE_URI}/${name}`, {
                    method: 'GET',
                    headers: {'Content-Type': 'text/plain'}
                }
            )
                .then((response) => {
                    return response.text();
                })
                .then((data) => {
                    setValue(data);
                    return data;
                })
                .catch((err) => {
                    console.error(err);
                })
        }, updateInterval);

        return () => clearInterval(interval);
    }, [])

    return (
        <div className="info-card">
            <h2>{name}</h2>
            <pre>
                {value}
            </pre>
        </div>
    );
}

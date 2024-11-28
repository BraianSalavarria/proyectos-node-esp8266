function controlLed(accion) {
    const ip = document.getElementById('ip').value;
    if (!ip) {
        alert("Por favor, ingresa una IP válida.");
        return;
    }
    
    const url = `http://${ip}/${accion}`;
    
    fetch(url)
        .then(response => {
            if (response.ok) {
                return response.text();
            } else {
                throw new Error("No se pudo conectar al ESP8266.");
            }
        })
        .then(data => {
            console.log(data); // Muestra el mensaje de respuesta del servidor
            //alert(`LED ${accion === 'encender' ? 'encendido' : 'apagado'}`);
        })
        .catch(error => {
            console.error(error);
            alert("Error: No se pudo conectar al dispositivo.");
        });
}

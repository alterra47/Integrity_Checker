const fileInput = document.getElementById('file-input');
const statusPanel = document.getElementById('status-panel');
const hashOutput = document.getElementById('hash-output');
const metaInfo = document.getElementById('meta-info');

fileInput.addEventListener('change', async (e) => {
    const file = e.target.files[0];
    if(!file) return;

    statusPanel.style.display = 'block';
    hashOutput.textContent = "Calculating ...";
    hashOutput.style.color = "#8b949e";

    const formData = new FormData();
    formData.append('file', file);

    try{
        //send req to py backend
        const response = await fetch('/upload', {
            method: 'POST',
            body: formData
        });

        const data = await response.json();
        
        //update ui
        hashOutput.textContent = data.integrity_hash;
        hashOutput.style.color = "#58a6ff"
        metaInfo.textContent = `Processed by: ${data.processed_by}`
    }
    catch(error){
        hashOutput.textContent = "Error connecting to server.";
        hashOutput.style.color = "red";
    }
});
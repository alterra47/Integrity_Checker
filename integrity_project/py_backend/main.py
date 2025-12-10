import socket
import os
import shutil
from fastapi import FastAPI, UploadFile, HTTPException
from fastapi.staticfiles import StaticFiles
from fastapi.responses import FileResponse

app = FastAPI()
app.mount("/static", StaticFiles(directory="static"), name="static")

#serve index,html as welcome page
@app.get("/")
async def read_index():
    return FileResponse('static/index.html')

#config
CPP_HOST = "127.0.0.1"
CPP_PORT = 8080
TEMP_DIR = "temp_uploads"

os.makedirs(TEMP_DIR, exist_ok=True)

def query_cpp_engine(file_path: str) -> str:
    """
    Connect to cpp microservice , send the file
    and get hash response
    """
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((CPP_HOST, CPP_PORT))
            
            sock.sendall(file_path.encode('utf-8'))

            response = sock.recv(1024)

            return response.decode('utf-8')
    
    except ConnectionRefusedError:
        return "Error:C++ Engine is down."
    except Exception as e:
        return f"Error {str(e)}"
    
@app.post("/upload")
async def verify_file(file : UploadFile):
    """
    Endpoint for ui to upload file
    """
    temp_path = ""
    if(file.filename!=None):
        temp_path = os.path.join(TEMP_DIR, file.filename)
    else:
        return{
            "filename": file.filename,
            "integrity_hash": "Error:No filename provided",
            "processed_by": "C++ Backend" 
        }

    with open(temp_path, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)

    abs_path = os.path.abspath(temp_path)

    result = query_cpp_engine(abs_path)

    return {
        "filename": file.filename,
        "integrity_hash": result,
        "processed_by": "C++ Backend" 
    }
from fastapi import FastAPI

app = FastAPI(
    title="Rytmus",
    description="Backend for Rytmus app",
    version="1.0.0"
)

@app.get("/")
def main_menu():
    return "Welcome to Rytmus!"
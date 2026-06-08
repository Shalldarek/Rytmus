from fastapi import FastAPI
from api.app.routers import logs, statistics

app = FastAPI(
    title="Rytmus",
    description="Backend for Rytmus app",
    version="1.0.0"
)

app.include_router(logs.router)
app.include_router(statistics.router)

@app.get("/")
def main_menu():
    return "Welcome to Rytmus!"


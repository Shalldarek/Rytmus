from fastapi import FastAPI
from api.app.routers.logs import router

app = FastAPI(
    title="Rytmus",
    description="Backend for Rytmus app",
    version="1.0.0"
)

app.include_router(router)

@app.get("/")
def main_menu():
    return "Welcome to Rytmus!"


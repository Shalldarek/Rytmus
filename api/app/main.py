from datetime import date

from fastapi import Depends, FastAPI
from api.app import database, models, schemas
from sqlalchemy.orm import Session

models.Base.metadata.create_all(bind=database.engine)

app = FastAPI(
    title="Rytmus",
    description="Backend for Rytmus app",
    version="1.0.0"
)

def get_db():
    db = database.SessionLocal()
    try:
        yield db
    finally:
        db.close()

@app.get("/")
def main_menu():
    return "Welcome to Rytmus!"

@app.get("/logs/", response_model=list[schemas.DailyLogResponse])
def get_all_logs(db: Session = Depends(get_db)):
    return db.query(models.DailyLog).order_by(models.DailyLog.log_date.desc()).all()

@app.get("/logs/{log_date}", response_model=schemas.DailyLogResponse)
def get_log(log_date: str, db: Session = Depends(get_db)):
    log = db.query(models.DailyLog).filter(models.DailyLog.log_date == log_date).first()
    return log

def delete_daily_log(db: Session, log_date: date):
    db_log = db.query(models.DailyLog).filter(models.DailyLog.log_date == log_date).first()
    if db_log:
        db.delete(db_log)
        db.commit()
        return True
    return False


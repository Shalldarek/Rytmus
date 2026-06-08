from datetime import date
from fastapi import APIRouter, Depends
from sqlalchemy import desc
from sqlalchemy.orm import Session
from ..database import get_db
from .. import schemas
from api.app import database, models

models.Base.metadata.create_all(bind=database.engine)

router = APIRouter(
    prefix="/logs",
    tags=["Logs"]
)

@router.get("/", response_model=list[schemas.DailyLogResponse])
def get_all_logs(db: Session = Depends(get_db)):
    return db.query(models.DailyLog).order_by(models.DailyLog.log_date.desc()).all()

@router.get("/{log_date}", response_model=schemas.DailyLogResponse)
def get_log(log_date: str, db: Session = Depends(get_db)):
    log = db.query(models.DailyLog).filter(models.DailyLog.log_date == log_date).first()
    return log

@router.post("/", response_model=schemas.DailyLogResponse)
def post_log(log: schemas.DailyLogCreate, db: Session=Depends(get_db)):
    db_log = models.DailyLog(**log.model_dump())

    db.add(db_log)
    db.commit()
    db.refresh(db_log)

    return db_log


@router.delete("/{log_date}")
def delete_log(log_date: date, db: Session = Depends(get_db)):
    success = delete_daily_log(db, log_date)
    if not success:
        from fastapi import HTTPException
        raise HTTPException(
            status_code=404, 
            detail=f"Log {log_date} wasn't found."
        )
    return {"message": "Log deleted!"}

def delete_daily_log(db: Session, log_date: date):
    db_log = db.query(models.DailyLog).filter(models.DailyLog.log_date == log_date).first()
    if db_log:
        db.delete(db_log)
        db.commit()
        return True
    return False

@router.put("/{log_date}", response_model=schemas.DailyLogResponse)
def put_record(log_date: date, log_db: schemas.DailyLogCreate, db: Session=Depends(get_db)):
    log = db.query(models.DailyLog).filter(models.DailyLog.log_date == log_date).first()

    if log is None:
        return "No log with such a date in DB"
    
    log.sleep_hours = log_db.sleep_hours
    log.night_awakenings = log_db.night_awakenings
    log.coffees = log_db.coffees
    log.stress_level = log_db.stress_level
    log.water_liters = log_db.water_liters
    log.screen_time_hours = log_db.screen_time_hours
    log.workout = log_db.workout
    log.mood_level = log_db.mood_level
    
    db.commit()
    db.refresh(log)

    return log

@router.get("/statistics", response_model=schemas.DailyLogResponse)
def get_week_statistics(db: Session=Depends(get_db)):
    last_seven_records = db.query(models.DailyLog).order_by(desc(models.DailyLog.created_at)).limit(7).all()
    return last_seven_records
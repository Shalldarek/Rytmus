from fastapi import APIRouter, Depends
from sqlalchemy import desc
from sqlalchemy.orm import Session
from api.app import models
from api.app.database import get_db

router = APIRouter (
    prefix="/statistics",
    tags=["statistics"]
)

@router.get("/")
def get_week_statistics(db: Session=Depends(get_db)):
    last_seven_records = db.query(models.DayStatistics).order_by(desc(models.DayStatistics.created_at)).limit(7).all()
    return last_seven_records
from sqlalchemy import Column, Integer, Float, Boolean, Date, CheckConstraint
from .database import Base

class DailyLog(Base):
    __tablename__ = "daily_logs"

    log_date = Column(Date, primary_key=True, index=True)
    sleep_hours = Column(Float, nullable=False)
    night_awakenings = Column(Integer, default=0)
    coffees = Column(Integer, default=0)
    stress_level = Column(Integer, CheckConstraint('stress_level BETWEEN 1 AND 10'))
    water_liters = Column(Float, default=0.0)
    screen_time_hours = Column(Float, default=0.0)
    workout = Column(Boolean, default=False)
    mood_level = Column(Integer, CheckConstraint('mood_level BETWEEN 1 AND 10'))
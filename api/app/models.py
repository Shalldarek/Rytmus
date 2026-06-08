from sqlalchemy import TIMESTAMP, Column, Integer, Float, Boolean, Date, CheckConstraint, func
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

class DayStatistics(Base):
    __tablename__ = "day_statistics"

    id = Column(Integer, primary_key=True, autoincrement=True)
    log_date = Column(Date, nullable=False)
    sleep_hours = Column(Float)
    night_awakenings = Column(Integer)
    stress_level = Column(Integer)
    mood_level = Column(Integer)
    water_liters = Column(Float)
    coffees = Column(Integer)
    screen_time_hours = Column(Float)
    workout = Column(Boolean)
    score = Column(Integer)
    created_at = Column(TIMESTAMP, server_default=func.now())
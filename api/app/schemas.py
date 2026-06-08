from pydantic import BaseModel, Field
from datetime import date
from typing import Optional

class DailyLogBase(BaseModel):
    sleep_hours: float
    night_awakenings: Optional[int] = 0
    coffees: Optional[int] = 0
    stress_level: Optional[int] = Field(None, ge=1, le=10)
    water_liters: Optional[float] = 0.0
    screen_time_hours: Optional[float] = 0.0
    workout: Optional[bool] = False
    mood_level: Optional[int] = Field(None, ge=1, le=10)

class DailyLogCreate(DailyLogBase):
    log_date: date

class DailyLogResponse(DailyLogBase):
    log_date: date

    class Config:
        from_attributes = True

class DayStatisticsSchema(BaseModel):
    log_date: date
    sleep_hours: float
    night_awakenings: int
    stress_level: int
    mood_level: int
    water_liters: float
    coffees: int
    screen_time_hours: float
    workout: bool
    score: int  

    class Config:
        from_attributes = True
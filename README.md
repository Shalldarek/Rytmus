# Rytmus

Rytmus is a life-logging application designed to help you track and analyze your daily habits. It features a robust backend API for data management and a C++ worker for calculating daily performance scores.

## Architecture

The project is composed of two main services containerized with Docker for easy deployment and scalability.

-   **`api`**: A Python backend built with **FastAPI** that provides RESTful endpoints to create, retrieve, update, and delete daily logs. It uses SQLAlchemy for ORM and Pydantic for data validation.
-   **`worker`**: A C++ application that fetches log data from the API, processes it, and calculates a daily score based on predefined metrics. This allows for performance-critical data analysis to be offloaded from the main API.

## Features

-   **Daily Logging**: Track key wellness metrics.
-   **RESTful API**: Full CRUD functionality for managing logs.
-   **Data Analysis**: A C++ worker analyzes your logs to provide a daily score.
-   **Containerized**: Uses Docker and Docker Compose for a consistent development and deployment environment (In process)

### Tracked Metrics

-   Sleep Hours
-   Night Awakenings
-   Coffee Intake
-   Stress Level (1-10)
-   Water Intake (liters)
-   Screen Time (hours)
-   Workouts
-   Mood Level (1-10)

## Getting Started

### Prerequisites

-   Docker
-   Docker Compose

### Installation & Setup

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/shalldarek/rytmus.git
    cd rytmus
    ```

2.  **Configure the Database:**
    The application is configured to connect to a MySQL database. Update the connection string in `api/app/database.py` with your database credentials:
    ```python
    # api/app/database.py
    SQLALCHEMY_DATABASE_URL = "mysql+pymysql://<user>:<password>@<host>:<port>/<database>"
    ```

3.  **Build and run the containers:**
    From the root directory, run the following command:
    ```sh
    docker-compose up --build
    ```

The API will be available at `http://localhost:8000`.

## API Endpoints

The API provides the following endpoints under the `/logs` prefix:

| Method | Endpoint                | Description                     |
| :----- | :---------------------- | :------------------------------ |
| `GET`  | `/logs/`                | Retrieve all daily logs.        |
| `GET`  | `/logs/{log_date}`      | Retrieve a specific log by date.|
| `POST` | `/logs/`                | Create a new daily log.         |
| `PUT`  | `/logs/{log_date}`      | Update an existing log by date. |
| `DELETE`| `/logs/{log_date}`      | Delete a specific log by date.  |

### Example Usage with `curl`

**Create a new log:**
```sh
curl -X POST "http://localhost:8000/logs/" -H "Content-Type: application/json" -d '{
  "log_date": "2023-10-27",
  "sleep_hours": 8,
  "night_awakenings": 0,
  "coffees": 1,
  "stress_level": 3,
  "water_liters": 2.5,
  "screen_time_hours": 5,
  "workout": true,
  "mood_level": 8
}'
```

**Get all logs:**
```sh
curl http://localhost:8000/logs/
```

## Technologies Used

-   **Backend**: Python, FastAPI, Uvicorn, SQLAlchemy, PyMySQL
-   **Worker**: C++, cpr, nlohmann/json
-   **Database**: MySQL
-   **Containerization**: Docker, Docker Compose

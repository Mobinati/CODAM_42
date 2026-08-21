from abc import ABC, abstractmethod
from typing import ANY


class DataProcessor(ABC):
    def __init__(self) -> None:
        self.data: list[tuple[int, str]] = []
        self.rank: int = 0


    @abstractmethod
    def validate(self, data: ANY) -> bool:
        pass


    @abstractmethod
    def ingest(self, data: ANY) -> None:
        try:
            validate(data)
        
        except Exception as e:
            print(f"Error: {e}")

    def output(self) -> tuple[int, str]:
        if self.data:
            return self.data.pop(0)
        else:
            raise IndexError("No data available")

class NumericProcessor(DataProcessor):
    def validate(self, data = ANY) -> bool:
        super().validate()
        if isinstance(data, (int, float)) and not isinstance(data, bool):
            return True

        if isinstance(data, list):
            return all(
                isinstance(item, (int, float)) and not isinstance(item, bool)
                for item in list
            )
        print(f"Trying to validate input 'f{data}:' {data.isinteger}")

        
    def ingest(self, data: int | float | list[int | float] ) -> None:
        if 


    

class TextProcessor(DataProcessor):
    super().validate()


class LogProcessor(DataProcessor):
    super().validate()

    def ingest(self, data: dict) -> str


#!/usr/bin/env python3

from abc import ABC, abstractmethod
from typing import Any, Protocol


class DataProcessor(ABC):
    def __init__(self) -> None:
        self.data: list[tuple[int, str]] = []
        self.rank: int = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        pass

    def output(self) -> tuple[int, str]:
        if self.data:
            return self.data.pop(0)
        else:
            raise IndexError("No data available")


class ExportPlugin(Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        ...


class DataStream():
    def __init__(self) -> None:
        self.processors: list[DataProcessor] = []

    def register_processor(self, proc: DataProcessor) -> None:
        self.processors.append(proc)

    def process_stream(self, stream: list[Any]) -> None:
        for item in stream:
            found = False
            for processor in self.processors:
                if processor.validate(item):
                    processor.ingest(item)
                    found = True
                    break
            if not found:
                print(f"DataStream error - "
                      f"Can't process element in stream:{item}")

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")
        if not self.processors:
            print("No processor found, no data")
            return

        for processor in self.processors:
            name = processor.__class__.__name__
            print(f"{name}: "
                  f"total {processor.rank} items processed,"
                  f"remaining {len(processor.data)} on processor")

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        for processor in self.processors:
            output_data = []

            for i in range(nb):

                if not processor.data:
                    break

            output_data.append(processor.output())

        if output_data:
            plugin.process_output(output_data)


class NumericProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, (int, float)) and not isinstance(data, bool):
            return True

        if isinstance(data, list):
            return all(
                isinstance(item, (int, float)) and not isinstance(item, bool)
                for item in data
            )

        else:
            return False

    def ingest(self, data: int | float | list[int | float]) -> None:
        if not self.validate(data):
            raise TypeError("Improper numeric data")

        if isinstance(data, list):
            for item in data:
                self.data.append((self.rank, str(item)))
                self.rank += 1
        else:
            self.data.append((self.rank, str(data)))
            self.rank += 1


class TextProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, str):
            return True

        if isinstance(data, list):
            return (all(isinstance(item, str) for item in data))

        return False

    def ingest(self, data: str | list[str]) -> None:
        if not self.validate(data):
            raise TypeError("Improper str data")

        if isinstance(data, list):
            for item in data:
                self.data.append((self.rank, str(item)))
                self.rank += 1
        else:
            self.data.append((self.rank, str(data)))
            self.rank += 1


class LogProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, dict):
            return all(
                isinstance(key, str) and isinstance(value, str)
                for key, value in data.items())

        if isinstance(data, list):
            return all(
                isinstance(item, dict)
                and all(
                    isinstance(key, str) and isinstance(value, str)
                    for key, value in item.items()
                )
                for item in data
            )
        return False

    def ingest(
        self,
        data: dict[str, str] | list[dict[str, str]]
    ) -> None:
        if not self.validate(data):
            raise TypeError("Improper log data")

        if isinstance(data, list):
            for item in data:
                self.data.append((self.rank, str(item)))
                self.rank += 1
        if isinstance(data, dict):
            self.data.append((self.rank, str(dict)))
            self.rank += 1


class CSVPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        values = []
        for rank, value in data:
            values.append(value)

        print(f"CSV Output: {','.join(values)}")


class JSONPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        values = []
        for rank, value in data:
            values.append(f'"item_{rank}": "{value}"')

        output = "{" + ','.join(values) + "}"
        print(f"JSON Output: {output}")


def main() -> None:
    print("=== Code Nexus - Data Pipeline ===")

    print("Initialize Data Stream...")
    data_stream = DataStream()

    data_stream.print_processors_stats()

    print("Registering Processors")
    numeric = NumericProcessor()
    text = TextProcessor()
    log = LogProcessor()

    data_stream.register_processor(numeric)
    data_stream.register_processor(text)
    data_stream.register_processor(log)

    data = [
        "Hello world",
        [3.14, -1, 2.71],
        [
            {
                "log_level": "WARNING",
                "log_message": "Telnet access! Use ssh instead",
            },
            {
                "log_level": "INFO",
                "log_message": "User wil is connected",
            },
        ],
        42,
        ["Hi", "five"],
    ]

    print("Send first batch of data on stream:")
    print(data)

    data_stream.process_stream(data)

    data_stream.print_processors_stats()

    print("Send 3 processed data from each processor to a CSV plugin:")
    csv_plugin = CSVPlugin()
    data_stream.output_pipeline(3, csv_plugin)

    data_stream.print_processors_stats()

    data2 = [
        21,
        ["I love AI", "LLMs are wonderful", "Stay healthy"],
        [
            {
                "log_level": "ERROR",
                "log_message": "500 server crash",
            },
            {
                "log_level": "NOTICE",
                "log_message": "Certificate expires in 10 days",
            },
        ],
        [32, 42, 64, 84, 128, 168],
        "World hello",
    ]

    print("Send another batch of data:")
    print(data2)

    data_stream.process_stream(data2)

    data_stream.print_processors_stats()

    print("Send 5 processed data from each processor to a JSON plugin:")
    json_plugin = JSONPlugin()
    data_stream.output_pipeline(5, json_plugin)

    data_stream.print_processors_stats()


if __name__ == "__main__":
    main()

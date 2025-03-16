import pytest
import re
import subprocess
import sys

from glob import iglob
from typing import List

TEST_CASE_REGEX = re.compile(r"// TEST: (.*) -> (.*)")


def discover_test_cases() -> List["pytest.mark.structures.ParameterSet"]:
    test_cases = []

    for src_path in iglob("src/**/*.cpp"):
        print(f"Scanning {src_path}...", file=sys.stderr)
        with open(src_path, "r", encoding="utf-8") as fobj:
            num_cases = 0
            for line in fobj:
                match = TEST_CASE_REGEX.search(line)
                if match is not None:
                    print(match.group(0).strip(), file=sys.stderr)
                    test_cases.append(
                        pytest.param(
                            src_path,
                            match.group(1).strip() + "\n",
                            match.group(2).strip(),
                            id=f"{src_path}/{num_cases}"))
                    num_cases += 1

    return test_cases


@pytest.mark.parametrize("src_path,stdin,expected_stdout", discover_test_cases())
def test_problem(src_path: str, stdin: str, expected_stdout: str) -> None:
    result = subprocess.run(
        ["./run", src_path],
        input=stdin,
        encoding="utf-8",
        capture_output=True,
        timeout=10,
        check=True)

    assert result.stdout.strip() == expected_stdout

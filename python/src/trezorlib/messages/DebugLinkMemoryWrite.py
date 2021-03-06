# Automatically generated by pb2py
# fmt: off
from .. import protobuf as p

if __debug__:
    try:
        from typing import Dict, List  # noqa: F401
        from typing_extensions import Literal  # noqa: F401
    except ImportError:
        pass


class DebugLinkMemoryWrite(p.MessageType):
    MESSAGE_WIRE_TYPE = 112

    def __init__(
        self,
        *,
        address: int = None,
        memory: bytes = None,
        flash: bool = None,
    ) -> None:
        self.address = address
        self.memory = memory
        self.flash = flash

    @classmethod
    def get_fields(cls) -> Dict:
        return {
            1: ('address', p.UVarintType, None),
            2: ('memory', p.BytesType, None),
            3: ('flash', p.BoolType, None),
        }

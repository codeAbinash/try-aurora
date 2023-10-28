import { createRef, useEffect, useState } from "react";
import { Aurora } from "aurora-react";
import "aurora-code/themes/one dark pro";

const options = [
  {
    name: "Docs",
    link: "https://github.com/codeAbinash/aurora-react",
  },
  {
    name: "Aurora Core",
    link: "https://github.com/codeAbinash/aurora",
  },
  {
    name: "Aurora React",
    link: "https://github.com/codeAbinash/aurora-react",
  },
];

async function loadCode() {
  // const res = await fetch(
  //   "https://codeabinash.github.io/aurora/test/example.c"
  // );
  const res = await fetch("/example.c");
  let code = await res.text();
  code = code.replace(/\r/g, "");
  return code;
}

function App() {
  const [code, setCode] = useState("");
  const textAreaRef = createRef<HTMLTextAreaElement>();
  const auroraRef = createRef<HTMLDivElement>();
  const [highlightingTime, setHighlightingTime] = useState(2);
  async function load() {
    const code = await loadCode();
    setCode(code);
  }
  useEffect(() => {
    load();
  }, []);

  return (
    <div className="gap-5 min-h-[100dvh] flex-col flex justify-center items-center bg-gray-800">
      <div className="flex gap-3 justify-center items-center flex-wrap px-5 pt-5 text-xs lg:text-sm">
        <a
          href="https://github.com/codeAbinash/aurora-react"
          target="_blank"
          className="bg-gray-950 px-7 p-3 rounded-full cursor-pointer"
        >
          <img src="/aurora.png" className="h-[0.8rem]" />
        </a>
        <div className="bg-gray-950 text-white gap-5 p-2 px-7 rounded-full flex">
          <p className="custom-font font-medium">
            Highlighted {(code.match(/\n/g) || []).length} lines in{" "}
            <span className="text-yellow-400">
              ✨ {highlightingTime.toFixed(1)} ms
            </span>
          </p>
        </div>
        {options.map((option) => {
          return (
            <a
              href={option.link}
              className="bg-gray-950 text-white gap-5 p-2 px-7 rounded-full flex"
              target="_blank"
              rel="noreferrer"
            >
              <p className="custom-font font-medium">{option.name}</p>
            </a>
          );
        })}
      </div>
      <div className="px-5 w-full">
        <div className="rounded-xl overflow-hidden w-full max-w-[100rem] h-[80dvh] mx-auto">
          <div className="grid  text-sm lg:text-base grid-cols-1 lg:grid-cols-2 space-between h-full bg-gray-900 font-medium text-gray-300 custom-font">
            <div
              className="p-7 overflow-scroll custom-scrollbar z-10 h-[40dvh] lg:h-full"
              ref={auroraRef}
              onScroll={(e) => {
                if (textAreaRef.current) {
                  textAreaRef.current.scrollTop = e.currentTarget.scrollTop;
                  textAreaRef.current.scrollLeft = e.currentTarget.scrollLeft;
                }
              }}
            >
              <Aurora code={code} setTime={setHighlightingTime} />
            </div>

            <textarea
              className="resize-none whitespace-pre p-7 bg-gray-950 border-none outline-none custom-scrollbar custom-font h-[40dvh] lg:h-full z-20"
              ref={textAreaRef}
              tabIndex={-1}
              spellCheck={false}
              value={code}
              onInput={(e) => {
                setCode(e.currentTarget.value);
              }}
              onScroll={(e) => {
                if (auroraRef.current) {
                  auroraRef.current.scrollTop = e.currentTarget.scrollTop;
                  auroraRef.current.scrollLeft = e.currentTarget.scrollLeft;
                }
              }}
            ></textarea>
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;

import { nodeGenerator, tokenizer, Node } from 'aurora-code'
import 'aurora-code/themes/oneDarkPro.css'
import { Aurora } from 'aurora-react'
import { createRef, useEffect, useState } from 'react'

const options = [
  {
    name: 'Docs',
    link: 'https://github.com/codeAbinash/aurora-react',
    image: '/github.svg',
  },
  {
    name: 'Aurora Core',
    link: 'https://github.com/codeAbinash/aurora',
    image: '/github.svg',
  },
  {
    name: 'Aurora React',
    link: 'https://github.com/codeAbinash/aurora-react',
    image: '/github.svg',
  },
]

async function loadCode() {
  // const res = await fetch(
  //   "https://codeabinash.github.io/aurora/test/example.c"
  // );
  const res = await fetch('/example.c')
  let code = await res.text()
  code = code.replace(/\r/g, '')
  return code
}

function App() {
  const [code, setCode] = useState('')
  const textAreaRef = createRef<HTMLTextAreaElement>()
  const auroraRef = createRef<HTMLDivElement>()
  const [highlightingTime, setHighlightingTime] = useState(2)
  async function load() {
    const code = await loadCode()
    setCode(code)
  }
  useEffect(() => {
    load()
  }, [])

  return (
    <div className='flex min-h-[100dvh] flex-col items-center gap-5 bg-gray-800'>
      <div className='mt-4 flex flex-wrap items-center justify-center gap-3 px-5 text-xs lg:text-sm'>
        <a
          href='https://github.com/codeAbinash/aurora-react'
          target='_blank'
          className='cursor-pointer rounded-full bg-gray-950 p-3 px-7'
        >
          <img src='/aurora.png' className='h-[0.8rem]' />
        </a>
        <div className='flex gap-5 rounded-full bg-gray-950 p-2 px-7 text-white'>
          <p className='custom-font font-medium'>
            Highlighted {(code.match(/\n/g) || []).length} lines in{' '}
            <span className='text-yellow-400'>✨ {highlightingTime.toFixed(1)} ms</span>
          </p>
        </div>
        {options.map((option) => {
          return (
            <a
              href={option.link}
              className='flex items-center justify-center gap-2 rounded-full bg-gray-950 p-2 px-7 text-white'
              target='_blank'
              rel='noreferrer'
              key={option.name}
            >
              <img src={option.image} className='h-[0.9rem]' />
              <p className='custom-font font-medium'>{option.name}</p>
            </a>
          )
        })}
      </div>
      <div className='w-full px-5'>
        <div className='mx-auto h-[90dvh] w-full overflow-hidden rounded-xl'>
          <div className='space-between custom-font grid h-full grid-cols-2 bg-gray-900 text-sm font-medium text-gray-300 lg:grid-cols-11 lg:text-base'>
            <div
              className='custom-scrollbar z-10 col-span-4 h-[40dvh] overflow-scroll p-7 lg:h-full'
              ref={auroraRef}
              onScroll={(e) => {
                if (textAreaRef.current) {
                  textAreaRef.current.scrollTop = e.currentTarget.scrollTop
                  textAreaRef.current.scrollLeft = e.currentTarget.scrollLeft
                }
              }}
            >
              <Aurora code={code} setTime={setHighlightingTime} />
            </div>
            <textarea
              className='custom-scrollbar custom-font z-20 col-span-4 h-[40dvh] resize-none whitespace-pre border-none bg-gray-950 p-7 outline-none lg:h-full'
              ref={textAreaRef}
              tabIndex={-1}
              spellCheck={false}
              value={code}
              autoFocus={true}
              onInput={(e) => {
                setCode(e.currentTarget.value)
              }}
              onScroll={(e) => {
                if (auroraRef.current) {
                  auroraRef.current.scrollTop = e.currentTarget.scrollTop
                  auroraRef.current.scrollLeft = e.currentTarget.scrollLeft
                }
              }}
            ></textarea>
            <TokensArea code={code} />
          </div>
        </div>
      </div>
    </div>
  )
}

function TokensArea({ code }: { code: string }) {
  const [tokens, setTokens] = useState<Node[]>([])
  const [isTokenShown, setIsTokenShown] = useState(false)

  useEffect(() => {
    if (!isTokenShown) return
    setTokens(nodeGenerator(tokenizer(code)))
  }, [code, isTokenShown])

  if (!isTokenShown)
    return (
      <div className='custom-scrollbar z-10 col-span-3 h-[40dvh] overflow-scroll p-7 lg:h-full'>
        <div className='flex h-full flex-col items-center justify-center gap-8'>
          <img src='/aurora.png' className='w-2/3 opacity-70' />
          <button
            onClick={() => setIsTokenShown(true)}
            className='cursor-pointer rounded-full bg-blue-500 p-2 px-7 text-sm text-white hover:bg-blue-600'
          >
            Show Tokens
          </button>
          <div>
            <p className='text-center text-sm text-gray-400'>Showing tokens will require more computation.</p>
            <p className='text-center text-sm text-yellow-400'>Try typing in the editor on the left side.</p>
          </div>
        </div>
      </div>
    )

  return (
    <div className='custom-scrollbar relative z-10 col-span-3 h-[40dvh] overflow-scroll p-7 lg:h-full'>
      {/* <div className="flex flex-col gap-2 fixed bg-gray-700/50 px-5 py-2 backdrop-blur-md right-0 mr-10 -mt-3 rounded-full">
        <p className="text-gray-300 text-sm">
          <span className="text-yellow-400">✨ {tokens.length}</span> tokens
        </p>
      </div> */}
      <div className='prose-base rounded-sm'>
        <h1 className='text-xl text-gray-300'>Tokens ({tokens.length})</h1>
        <table>
          <thead className='border border-gray-800'>
            <tr>
              <th className='pb-2 pt-2'>Token Value</th>
              <th className='pb-2 pt-2'>Token Type</th>
            </tr>
          </thead>
          <tbody>
            {tokens.map((token, index) => {
              return <TokenElement key={index} node={token} />
            })}
          </tbody>
        </table>
      </div>
    </div>
  )
}

const skipTypes = ['whitespace', 'comment_start', 'comment_end', 'quote angle', 'quote double', 'quote single']

function TokenElement({ node }: { node: Node }) {
  if (skipTypes.includes(node.type)) return null
  return (
    <tr className='border border-gray-800'>
      <td className={`text-gray-400`}>
        <span className={`aurora-${node.type} inline-block cursor-pointer rounded-md pl-5`}>{node.value}</span>
      </td>
      <td className='text-gray-400'>{node.type}</td>
    </tr>
  )
}

export default App

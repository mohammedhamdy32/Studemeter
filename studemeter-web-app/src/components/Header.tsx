import Link from "next/link";

interface BackButtonParams {
  text: string;
  href: string;
}

function BackButton({text, href}: BackButtonParams) {
  return (
    <div className="row">
      <Link href={href} className="btn btn-sm btn-primary col-auto text-uppercase rounded-pill btn-light opacity-75">
        <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-left-fill" viewBox="0 0 16 16">
          <path d="m3.86 8.753 5.482 4.796c.646.566 1.658.106 1.658-.753V3.204a1 1 0 0 0-1.659-.753l-5.48 4.796a1 1 0 0 0 0 1.506z" />
        </svg>
        {text}
      </Link>
    </div>
  );
}

function Header({ text, href }: BackButtonParams) {
  return (
    <header className="row">
      {text && href && <BackButton text={text} href={href} />}
      <div className="col">
        <div className="row justify-content-center">
          <h1 className="py-4 text-center col-12 row justify-content-center">
            <img className="col-12" height="48" src="/logo.svg" alt="Logo" />
            <span className="mt-2 h5 text-body-emphasis opacity-75">
              Students Focus Monitoring System
            </span>
          </h1>
        </div>
      </div>
    </header>
  );
}

export default Header;

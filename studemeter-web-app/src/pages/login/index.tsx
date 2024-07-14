import Head from "next/head";
import Container from "react-bootstrap/Container";
import Header from "@/components/Header";
import Link from "next/link";
import { useRouter } from 'next/router';

export default function Home() {
  const router = useRouter();
  const handleButtonClick = () => {
    router.push('/teacher');
  }

  return (
    <>
      <Head>
        <title>Studemeter</title>
        <meta name="description" content="Students Focus Monitoring System" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <Container as="main" className="py-4 px-3 mx-auto">
        <Header text="back" href="/" />

        <div className="row justify-content-center">
          <form className="col-lg-6 row">
            <label className="text-muted fs-6 text-center mb-2 text-uppercase">
              Enter your info
            </label>

            <div className="col-12 mb-2 input-group-lg">
              <label className="visually-hidden" htmlFor="nationalId">National ID</label>
              <input type="number" className="form-control rounded-4 text-center" id="nationalId" placeholder="National ID" />
            </div>

            <div className="col-12 mb-4 input-group-lg">
              <label className="visually-hidden" htmlFor="passkey">Passkey</label>
              <input type="password" className="form-control rounded-4 text-center" id="passkey" placeholder="Passkey" />
            </div>

            <div className="col-12">
              <div className="row justify-content-center">
                <button type="button" onClick={handleButtonClick} className="text-capitalize btn btn-primary rounded-pill col-auto">
                  Login
                  <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-right-fill" viewBox="0 0 16 16">
                    <path d="m12.14 8.753-5.482 4.796c-.646.566-1.658.106-1.658-.753V3.204a1 1 0 0 1 1.659-.753l5.48 4.796a1 1 0 0 1 0 1.506z" />
                  </svg>
                </button>
              </div>
            </div>
          </form>
        </div>
      </Container >
    </>
  );
}

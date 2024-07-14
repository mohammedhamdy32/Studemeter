import Head from "next/head";
import Container from "react-bootstrap/Container";
import Header from "@/components/Header";
import Link from "next/link";

export default function Home() {
  return (
    <>
      <Head>
        <title>Studemeter</title>
        <meta name="description" content="Students Focus Monitoring System" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <Container as="main" className="py-4 px-3 mx-auto">
        <Header text="" href="" />

        <div className="row justify-content-center">
          <div className="col-auto">
            <img className="img-fluid my-5 rounded-5 opacity-75" src="/img/classroom.jpg" alt="" />
          </div>
        </div>

        <div className="row justify-content-center">
          <Link href="/login" className="text-capitalize col-auto btn btn-primary rounded-pill">
            Login
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-right-fill" viewBox="0 0 16 16">
              <path d="m12.14 8.753-5.482 4.796c-.646.566-1.658.106-1.658-.753V3.204a1 1 0 0 1 1.659-.753l5.48 4.796a1 1 0 0 1 0 1.506z" />
            </svg>
          </Link>
        </div>
      </Container >
    </>
  );
}
